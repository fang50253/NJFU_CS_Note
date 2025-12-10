package com.mvc.action;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
 
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
 
@Controller
public class OtherExampleController {
 
   
   @RequestMapping("/somePath")
   public String requestResponseExample(HttpServletRequest request,
           HttpServletResponse reponses, Model model) {
 
	   String aaa=(String) request.getParameter("aaa");
	   model.addAttribute("message", "Hello Spring MVC Framework!"+aaa);

	   
 
       return "someView";
   }
 
}
