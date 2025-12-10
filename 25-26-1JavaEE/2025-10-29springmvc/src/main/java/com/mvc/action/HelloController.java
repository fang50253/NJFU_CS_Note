package com.mvc.action;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.ui.ModelMap;

@Controller
@RequestMapping("/hello")
public class HelloController{

   public HelloController() {

      System.out.println("Hello Controller construction!");
   }

   @RequestMapping(method = RequestMethod.GET)
  // @RequestMapping(method = RequestMethod.POST)
   public String printHello(ModelMap model) {
      System.out.println(" print hello");
      model.addAttribute("message111", "Hello Spring MVC Framework!");

      return "hello";
   }

}