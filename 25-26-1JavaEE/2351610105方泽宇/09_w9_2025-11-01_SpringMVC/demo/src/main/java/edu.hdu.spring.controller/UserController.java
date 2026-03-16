package edu.hdu.spring.controller;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.web.servlet.ModelAndView;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.ModelAttribute;

@Controller
public class UserController{
    
    @RequestMapping("/jsp/user.do")
    public ModelAndView handle(@ModelAttribute("user") User user) throws Exception {
        System.out.println(user);
        return new ModelAndView("success");
    }
}