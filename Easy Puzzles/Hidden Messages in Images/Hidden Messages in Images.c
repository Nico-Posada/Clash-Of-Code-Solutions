main(w, h, n, num, i) {
    scanf("%d%d", &w, &h);
    for (i = 1; i <= h*w; ++i) {
        scanf("%d", &n);
        num |= n%2;
        if (!(i%8) && i && printf("%c", num))
            num = 0;
        num <<= 1;
    }
}
