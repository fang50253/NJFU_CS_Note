package com.mvc.action;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
 
@Controller
public class RequestParamExampleController {
     
    @RequestMapping("/user")
    public String userInfo(Model model,
            @RequestParam(value = "name", defaultValue = "Guest") String name) {
 
        model.addAttribute("name", name);
 
        if("admin".equals(name)) {
            model.addAttribute("email", "admin@yiibai.com"+name);
        } else{
            model.addAttribute("email", "Not set"+name);
        }
        return "userInfo";
    }
  
}