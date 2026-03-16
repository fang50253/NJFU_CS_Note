package com.tempconvert.servlet;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

// 处理温度转换的Servlet
public class TempConvertServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // 1. 设置响应编码，避免中文乱码
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();

        // 2. 获取前端输入的摄氏温度
        String ctempStr = request.getParameter("ctemp");

        // 3. 校验输入是否为空
        if (ctempStr == null || ctempStr.trim().isEmpty()) {
            out.println("<html><body style='font-family: 宋体; padding: 20px;'>");
            out.println("<h3>错误：请输入有效的摄氏温度！</h3>");
            out.println("<a href='tempconvert0.html'>返回重新输入</a>");
            out.println("</body></html>");
            return;
        }

        try {
            // 4. 转换为数字并计算华氏温度（公式：华氏度 = 摄氏度 × 9/5 + 32）
            double ctemp = Double.parseDouble(ctempStr);
            double ftemp = ctemp * 9 / 5 + 32;

            // 5. 输出转换结果
            out.println("<html><head><title>转换结果</title></head>");
            out.println("<body style='font-family: 宋体; padding: 20px;'>");
            out.println("<h3>转换成功！</h3>");
            out.println("<p>" + ctemp + " ℃ = " + String.format("%.2f", ftemp) + " ℉</p>"); // 保留2位小数
            out.println("<a href='tempconvert0.html'>继续转换</a>");
            out.println("</body></html>");
        } catch (NumberFormatException e) {
            // 处理非数字输入的异常
            out.println("<html><body style='font-family: 宋体; padding: 20px;'>");
            out.println("<h3>错误：请输入数字格式的温度！</h3>");
            out.println("<a href='tempconvert0.html'>返回重新输入</a>");
            out.println("</body></html>");
        } finally {
            out.close();
        }
    }
}