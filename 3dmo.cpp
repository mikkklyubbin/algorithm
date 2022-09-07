void go(int a_l, int a_r, int time) {
    while (t < time) {
        t++;
        if (rolls[t].first != -1) {
            rolls_back[t] = {rolls[t].first, a[rolls[t].first]};
            if (l <= rolls[t].first && rolls[t].first < r) {
                adda(rolls[t].first, rolls[t].second - a[rolls[t].first]);
            }
            else{
                a[rolls[t].first] = rolls[t].second;
            }
        }
    }

    while (t > time) {
        if (rolls_back[t].first != -1 ) {
            if (l <= rolls_back[t].first && rolls_back[t].first < r) {
                adda(rolls_back[t].first, rolls_back[t].second - a[rolls_back[t].first]);
            }
            else{
                a[rolls_back[t].first] = rolls_back[t].second;
            }
        }
        t--;
    }


    while (a_r > r) {
        addcounter(a[r], +1);
        r++;
    }
    while (a_l < l) {
        l--;
        addcounter(a[l], +1);
    }
    while (a_r < r) {
        r--;
        addcounter(a[r], -1);
    }
    while (a_l > l) {
        addcounter(a[l], -1);
        l++;
    }
}
