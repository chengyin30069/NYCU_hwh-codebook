const int INF = 1e9;
Pt circumcenter(Pt A, Pt B, Pt C) {
    // a1(x-A.x) + b1(y-A.y) = c1
    // a2(x-A.x) + b2(y-A.y) = c2
    // solve using Cramer's rule
    T a1 = B.x - A.x, b1 = B.y - A.y, c1 = dis2(A, B) / 2.0;
    T a2 = C.x - A.x, b2 = C.y - A.y, c2 = dis2(A, C) / 2.0;
    T D = Pt(a1, b1) ^ Pt(a2, b2);
    T Dx = Pt(c1, b1) ^ Pt(c2, b2);
    T Dy = Pt(a1, c1) ^ Pt(a2, c2);
    if (D == 0) return Pt(-INF, -INF);
    return A + Pt(Dx / D, Dy / D);
}
Pt center;
T r2;
void minEncloseCircle(vector<Pt> pts) {
    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
    shuffle(pts.begin(), pts.end(), gen);
    center = pts[0], r2 = 0;

    for (int i = 0; i < pts.size(); i++) {
        if (dis2(center, pts[i]) <= r2) continue;
        center = pts[i], r2 = 0;
        for (int j = 0; j < i; j++) {
            if (dis2(center, pts[j]) <= r2) continue;
            center = (pts[i] + pts[j]) / 2.0;
            r2 = dis2(center, pts[i]);
            for (int k = 0; k < j; k++) {
                if (dis2(center, pts[k]) <= r2) continue;
                center = circumcenter(pts[i], pts[j], pts[k]);
                r2 = dis2(center, pts[i]);
            }
        }
    }
}