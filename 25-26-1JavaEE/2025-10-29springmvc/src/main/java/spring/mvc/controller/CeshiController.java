package spring.mvc.controller;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;
import org.springframework.web.servlet.mvc.AbstractController;

import javax.servlet.http.HttpServletRequest;

public class CeshiController  extends AbstractController {
	public CeshiController() {

		System.out.println("CeshiController construction !!!");
	}

	@Override
	 protected ModelAndView handleRequestInternal(HttpServletRequest request,
	                                                 javax.servlet.http.HttpServletResponse response) throws Exception {

	        System.out.println(request.getRequestURI());  // ��ȡController�����ƣ�����ַ
	        return new ModelAndView("index");  // �߼���
   }
}