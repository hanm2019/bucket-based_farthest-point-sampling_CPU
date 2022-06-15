/* functional  */

int to_int(std::string str) {
    int numl = 0;
    for (int i = 0; i < str.length(); i++) {
        numl *= 10;
        numl += str[i] - '0';
    }
    return numl;
}

std::string digit_to_6bit(int num) {
    std::string num_str = "";
    while (num) {
        num_str = char(num % 10 + 48) + num_str;
        num /= 10;
    }
    if (num_str.length() >= 6) return num_str;
    while (num_str.length() < 6) {
        num_str = "0" + num_str;
    }
    return num_str;
}
