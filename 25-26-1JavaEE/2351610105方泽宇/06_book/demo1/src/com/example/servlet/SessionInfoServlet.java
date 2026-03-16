package com.example.servlet;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.util.Date;

public class SessionInfoServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();

        // 1. 统计页面访问次数
        Integer visitCount = (Integer) session.getAttribute("visitCount");
        if (visitCount == null) {
            visitCount = 1; // 首次访问
        } else {
            visitCount++; // 非首次访问，次数+1
        }
        session.setAttribute("visitCount", visitCount);

        // 2. 设置其他Session属性
        session.setAttribute("username", "GuestUser");
        session.setAttribute("currentTime", new Date());

        // 3. 传递数据到JSP
        request.setAttribute("sessionId", session.getId());
        request.setAttribute("visitCount", visitCount);
        request.setAttribute("currentTime", new Date());

        // 转发到JSP
        request.getRequestDispatcher("/sessionInfo.jsp").forward(request, response);
    }
}