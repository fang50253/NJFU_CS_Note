

import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

// 使用注解映射 URL，和表单里的 action 保持一致
@WebServlet("/src/servlet/getdata")
public class getdata extends HttpServlet {
    private static final long serialVersionUID = 1L;

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // 设置响应内容类型和编码
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();

        try {
            // 获取表单参数
            String startStr = request.getParameter("start");
            String endStr = request.getParameter("end");

            int start = Integer.parseInt(startStr);
            int end = Integer.parseInt(endStr);

            // 简单逻辑：计算从 start 到 end 的和
            int sum = 0;
            for (int i = start; i <= end; i++) {
                sum += i;
            }
            // 输出结果到浏览器
            out.println("<html><body>");
            out.println("<h2>计算结果</h2>");
            out.println("<p>开始数字: " + start + "</p>");
            out.println("<p>结束数字: " + end + "</p>");
            out.println("<p>总和: " + sum + "</p>");
            out.println("</body></html>");
        } catch (NumberFormatException e) {
            out.println("<p>输入有误，请输入数字！</p>");
        } finally {
            out.close();
        }
    }
}