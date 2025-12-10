package edu.hdu.spring.aop;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
//import javax.xml.registry.infomodel.User;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.ui.ModelMap;
import org.springframework.validation.BindException;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.servlet.ModelAndView;
//import org.springframework.web.servlet.mvc.AbstractCommandController;
import org.springframework.web.servlet.mvc.AbstractController;

/*public class UserController extends AbstractCommandController {
   protected ModelAndView handle(HttpServletRequest request, HttpServletResponse response, Object command, BindException be) throws Exception {


        User user = (User)command;//�Զ���װ��User����
        System.out.println(user);
        //����springMVC-servlet.xml���ã���ͼ��ת��ת���success.jsp
        return new ModelAndView("success");
    }
}*/
@Controller
@RequestMapping("/user")
public class UserController {
    @RequestMapping(method = RequestMethod.POST)

   // protected ModelAndView handle(HttpServletRequest request, HttpServletResponse response, Model command) throws Exception {


    protected ModelAndView handle(HttpServletRequest request, HttpServletResponse response,User command) throws Exception {



        User user = (User)command;//�Զ���װ��User����
        System.out.println(user);
        //����springMVC-servlet.xml���ã���ͼ��ת��ת���success.jsp
        return new ModelAndView("success");
       /* ModelAndView mv = new ModelAndView("dataday/dataday_index");//日历控件处理
        String stationid=(String) request.getSession().getAttribute("stationid");
        mv.addObject("stationid",stationid);
        return mv;*/


    }


   /* @ModelAttribute
    public void userModel(String loginname,String password,
                          Model model){
        logger.info("userModel");
        // 创建User对象存储jsp页面传入的参数
        User user = new User();
        user.setLoginname(loginname);
        user.setPassword(password);
        // 将User对象添加到Model当中
        model.addAttribute("user", user);
    }

    @RequestMapping(value="/login1")
    public String login(Model model){
        logger.info("login");
        // 从Model当中取出之前存入的名为user的对象
        User user = (User) model.asMap().get("user");
        System.out.println(user);
        // 设置user对象的username属性
        user.setUsername("测试");
        return "result1";
    }*/

}