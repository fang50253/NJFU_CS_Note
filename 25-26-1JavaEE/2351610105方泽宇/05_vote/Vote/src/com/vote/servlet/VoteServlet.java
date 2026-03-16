package com.vote.servlet;

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

// 单例Servlet，静态计数器保证数据不丢失
public class VoteServlet extends HttpServlet {
    // 静态计数器：所有请求共享，重启Tomcat才会重置
    private static int familyCount = 0;
    private static int jobCount = 0;
    private static int emotionCount = 0;

    // 初始化时将自身存入ServletContext，供ResultServlet获取
    @Override
    public void init(ServletConfig config) throws ServletException {
        super.init(config);
        getServletContext().setAttribute("voteServlet", this);
    }

    // 获取票数的方法
    public int getFamilyCount() { return familyCount; }
    public int getJobCount() { return jobCount; }
    public int getEmotionCount() { return emotionCount; }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // 访问/vote时，直接跳转到投票页面
        request.getRequestDispatcher("vote.html").forward(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.setCharacterEncoding("UTF-8");
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();

        String action = request.getParameter("action");
        String option = request.getParameter("option");

        // 1. 处理“查看投票结果”：直接转发，无需任何条件
        if ("查看投票结果".equals(action)) {
            request.getRequestDispatcher("result").forward(request, response);
            return;
        }

        // 2. 处理“我要投票”：检查Cookie + 统计票数
        if ("我要投票".equals(action) && option != null) {
            // 检查是否已投票（Cookie）
            boolean hasVoted = false;
            Cookie[] cookies = request.getCookies();
            if (cookies != null) {
                for (Cookie cookie : cookies) {
                    if ("voted".equals(cookie.getName())) {
                        hasVoted = true;
                        break;
                    }
                }
            }

            if (hasVoted) {
                // 已投票提示
                out.println("<html><body style='font-family: 宋体; padding: 20px;'>");
                out.println("<h3>您已投过票，请勿重复投票！</h3>");
                out.println("<a href='vote.html'>返回投票页面</a> | <a href='result'>查看投票结果</a>");
                out.println("</body></html>");
            } else {
                // 未投票：统计票数
                switch (option) {
                    case "family": familyCount++; break;
                    case "job": jobCount++; break;
                    case "emotion": emotionCount++; break;
                }

                // 设置Cookie（有效期7天）
                Cookie voteCookie = new Cookie("voted", "true");
                voteCookie.setMaxAge(60 * 60 * 24 * 7);
                voteCookie.setPath("/");
                response.addCookie(voteCookie);

                // 投票成功提示
                out.println("<html><body style='font-family: 宋体; padding: 20px;'>");
                out.println("<h3>投票成功！感谢您的参与</h3>");
                out.println("<a href='vote.html'>返回投票页面</a> | <a href='result'>查看投票结果</a>");
                out.println("</body></html>");
            }
        }
    }
}