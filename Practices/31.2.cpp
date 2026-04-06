#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

struct Node {
    double x, y;
};

// 复数乘法： (x1+y1i) * (x2+y2i)
Node mul(double x1, double y1, double x2, double y2) {
    return {x1*x2 - y1*y2, x1*y2 + y1*x2};
}

// 复数除法： (x2+y2i) / (x1+y1i)
Node div(double x1, double y1, double x2, double y2) {
    double d = x1*x1 + y1*y1;
    return {(x1*x2 + y1*y2)/d, (x1*y2 - x2*y1)/d};
}

int main() {
    int n, m;
    cin >> n >> m;
    
    // 存储每个操作后的复合变换（用复数表示）
    Node chaa[100005];
    chaa[0] = {1.0, 0.0};  // 单位变换
    
    for (int i = 1; i <= n; i++) {
        int op;
        double val;
        cin >> op >> val;
        
        if (op == 1) {  // 拉伸
            chaa[i] = {chaa[i-1].x * val, chaa[i-1].y * val};
        } else {        // 旋转
            // 乘以 cosθ + i sinθ（逆时针旋转θ）
            chaa[i] = mul(chaa[i-1].x, chaa[i-1].y, cos(val), sin(val));
        }
    }
    
    cout << fixed << setprecision(2);  // 设置输出精度
    
    for (int t = 0; t < m; t++) {
        int i, j;
        double x, y;
        cin >> i >> j >> x >> y;
        
        // 计算从操作i到j的复合变换：chaa[j] / chaa[i-1]
        Node trans = div(chaa[i-1].x, chaa[i-1].y, chaa[j].x, chaa[j].y);
        
        // 应用变换到点(x,y)
        Node res = mul(trans.x, trans.y, x, y);
        
        cout << res.x << " " << res.y << endl;
    }
    
    return 0;
}