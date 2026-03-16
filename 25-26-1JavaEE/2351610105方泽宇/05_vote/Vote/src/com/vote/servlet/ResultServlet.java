package com.vote.servlet;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

public class ResultServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();

        // 获取VoteServlet实例（项目启动时已存入）
        VoteServlet voteServlet = (VoteServlet) getServletContext().getAttribute("voteServlet");

        // 即使无数据也能正常显示
        int family = voteServlet != null ? voteServlet.getFamilyCount() : 0;
        int job = voteServlet != null ? voteServlet.getJobCount() : 0;
        int emotion = voteServlet != null ? voteServlet.getEmotionCount() : 0;
        int total = family + job + emotion;

        // 生成结果页面
        out.println("<html><body style='font-family: 宋体; padding: 20px;'>");
        out.println("<h3>投票结果统计（总票数：" + total + "）</h3>");
        out.println("<ul>");
        out.println("<li>对家人好点：" + family + "票</li>");
        out.println("<li>找个自己喜欢的工作：" + job + "票</li>");
        out.println("<li>控制自己的情绪：" + emotion + "票</li>");
        out.println("</ul>");
        out.println("<a href='vote.html'>返回投票页面</a>");
        out.println("</body></html>");
    }

    // 兼容POST请求（避免转发时出错）
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}