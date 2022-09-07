import telebot
import sqlite3
from sqlite3 import Error
from telebot import types


def create_connection(path):
    connection = None
    try:
        connection = sqlite3.connect(path)
        print("Connection to SQLite DB successful")
    except Error as e:
        print(f"The error '{e}' occurred")

    return connection


def execute_query(connection, query):
    cursor = connection.cursor()
    try:
        cursor.execute(query)
        connection.commit()
        print("Query executed successfully")
    except Error as e:
        print(f"The error '{e}' occurred")


def execute_read_query(connection, query):
    cursor = connection.cursor()
    result = None
    try:
        cursor.execute(query)
        result = cursor.fetchall()
        return result
    except Error as e:
        print(f"The error '{e}' occurred")


TOKEN = "1794500036:AAFiPBjcpb0TfUyS2blz_NnP-tvGEtsfSe0"
bot = telebot.TeleBot(TOKEN)
drop = f"DROP TABLE users"
building = f"""
CREATE TABLE users (
    id          INTEGER,
    is_comand   BOOLEAN,
    is_solo     BOOLEAN,
    need_points INTEGER,
    PRIMARY KEY (
        id
    )
);
"""
need = True
if need:
    execute_query(create_connection("12.sqlite3"), drop)
    execute_query(create_connection("12.sqlite3"), building)


def yes_no(x):
    yes_no_keyboard = types.InlineKeyboardMarkup()
    key_yes = types.InlineKeyboardButton(text='Да', callback_data='yes' + str(x))  # кнопка «Да»
    yes_no_keyboard.add(key_yes)  # добавляем кнопку в клавиатуру
    key_no = types.InlineKeyboardButton(text='Нет', callback_data='no' + str(x))
    yes_no_keyboard.add(key_no)
    return yes_no_keyboard


all_item = ["инфа", "матеша", "русский", "физика"]


def get_keymap(ind, reverse = False):
    sql_quest = f"""
            SELECT
                need_points
            FROM
                users
            WHERE
                id = {ind}
            """
    q = int(str(execute_read_query(create_connection("12.sqlite3"), sql_quest)[0][0]))
    print(f"q = {q}")
    yes_no_keyboard = types.InlineKeyboardMarkup()
    key_yes = types.InlineKeyboardButton(text="Выход", callback_data=str(0))
    yes_no_keyboard.add(key_yes)
    for i in range(1, len(all_item) + 1):
        if q & (1 << i) == 0 and not reverse:
            print(all_item[i - 1])
            print(i)
            key_yes = types.InlineKeyboardButton(text=all_item[i - 1], callback_data=str(i))  # кнопка «Да»
            yes_no_keyboard.add(key_yes)  # добавляем кнопку в клавиатуру
        elif q & (1 << i) != 0 and reverse:
            print(all_item[i - 1])
            print(i)
            key_yes = types.InlineKeyboardButton(text=all_item[i - 1], callback_data=str(-i))  # кнопка «Да»
            yes_no_keyboard.add(key_yes)
    return yes_no_keyboard

print("Агсл")
@bot.message_handler(content_types=['text'])
def start(message):
    if message.text == '/reg':
        try:
            bot.delete_message(message.chat.id, message.message_id)
        except:
            print("no_to_del")
        default = 0
        sql_quest = f"""
        INSERT INTO
            users 
        VALUES
            ({message.from_user.id}, 0, 0, {default})
        """
        execute_query(create_connection("12.sqlite3"), sql_quest)
        sql_quest = f"""
                        UPDATE
                            users
                        SET
                            need_points = 0
                        WHERE
                            id = {message.from_user.id}
                        """

        execute_query(create_connection("12.sqlite3"), sql_quest)
        bot.send_message(message.from_user.id, text="Хотите ли вы получать уведомления о личных олимпиадах?",
                         reply_markup=yes_no(1))
    else:
        try:
            bot.delete_message(message.chat.id, message.message_id)
        except:
            print("no_to_del")
        bot.send_message(message.from_user.id, "Я вас не понимаю напишите /reg")
def edit(message):
    if message.text == '/add':
        try:
            bot.delete_message(message.chat.id, message.message_id)
        except:
            print("no_to_del")
        bot.send_message(message.chat.id, text="О каких предметах вы хотите получать уведомления?",
                         reply_markup=get_keymap(message.chat.id))
    if message.text == '/del':
        try:
            bot.delete_message(message.chat.id, message.message_id)
        except:
            print("no_to_del")
        bot.send_message(message.chat.id, text="О каких предметах вы не хотите получать уведомления?",
                         reply_markup=get_keymap(message.chat.id, True))



@bot.callback_query_handler(func=lambda call: call.data[-1] == '1'  and (call.data[0] == "y" or call.data[0] == "n"))
def callback_solo(call):
    print(3)
    if call.data == "yes":
        sql_quest = f"""
                        UPDATE
                            users
                        SET
                            is_solo = 1
                        WHERE
                            id = {call.message.chat.id}
                        """
        execute_query(create_connection("12.sqlite3"), sql_quest)
    bot.delete_message(call.message.chat.id, call.message.message_id)
    bot.send_message(call.message.chat.id, text="Хотите ли вы получать уведомления о командных олимпиадах?",
                     reply_markup=yes_no(2))


@bot.callback_query_handler(func=lambda call: call.data[-1] == '2' and (call.data[0] == "y" or call.data[0] == "n"))
def callback_comand(call):
    print(2)
    if call.data == "yes":
        sql_quest = f"""
                        UPDATE
                            users
                        SET
                            is_comand = 1
                        WHERE
                            id = {call.message.chat.id}
                        """
        execute_query(create_connection("12.sqlite3"), sql_quest)
    bot.delete_message(call.message.chat.id, call.message.message_id)
    bot.send_message(call.message.chat.id, text="О каких предметах вы хотите получать уведомления?",
                     reply_markup=get_keymap(call.message.chat.id))


@bot.callback_query_handler(func=lambda call: call.data.isdigit() or (call.data[0] == "-" and call.data[1:].isdigit()))
def callback_all(call):
    print(1)
    x = {}
    item = call.data
    sql_quest = f"""
    SELECT
        need_points
    FROM
        users
    WHERE
        id = {call.message.chat.id}
    """
    q = int(str(execute_read_query(create_connection("12.sqlite3"), sql_quest)[0][0]))
    if int(call.data) > 0:
        print((1 << int(call.data)))
        sql_quest = f"""
                            UPDATE
                                users
                            SET
                                need_points = {q + (1 << int(call.data))}
                            WHERE
                                id = {call.message.chat.id}
                            """
        execute_query(create_connection("12.sqlite3"), sql_quest)
        bot.delete_message(call.message.chat.id, call.message.message_id)
        bot.send_message(call.message.chat.id, text="О каких предметах вы хотите получать уведомления?",
                     reply_markup=get_keymap(call.message.chat.id))
    elif int(call.data) < 0:
        sql_quest = f"""
                                    UPDATE
                                        users
                                    SET
                                        need_points = {q - (1 << abs(int(call.data)))}
                                    WHERE
                                        id = {call.message.chat.id}
                                    """
        execute_query(create_connection("12.sqlite3"), sql_quest)
        bot.delete_message(call.message.chat.id, call.message.message_id)
        bot.send_message(call.message.chat.id, text="О каких предметах вы хотите получать уведомления?",
                         reply_markup=get_keymap(call.message.chat.id, True))
    else:
        mesg = bot.send_message(call.message.chat.id, 'Suc reg')
        bot.register_next_step_handler(mesg, edit)


bot.polling(none_stop=True, interval=0)
