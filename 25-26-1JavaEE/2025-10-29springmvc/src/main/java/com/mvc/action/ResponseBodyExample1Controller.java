package com.mvc.action;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;
 
@Controller
public class ResponseBodyExample1Controller {

    public ResponseBodyExample1Controller() {
        System.out.println(" ResponseBodyExample1Controller construction");

    }

    // Simple example, method returns String.
    @RequestMapping(value = "/saveResult")
    @ResponseBody
    public String authorInfo(Model model) {
        return "saved";
    }
 
     
}