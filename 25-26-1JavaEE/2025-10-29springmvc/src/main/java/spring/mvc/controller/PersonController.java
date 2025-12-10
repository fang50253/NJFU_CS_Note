package spring.mvc.controller;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Map;

import javax.annotation.Resource;
//import javax.servlet.http.HttpServletRequest;

import org.springframework.web.servlet.ModelAndView;
import spring.mvc.bean.Person;
import spring.mvc.service.*;
@Controller
//@RequestMapping("/person")
public class PersonController {
	public PersonController() {

		System.out.println("PersonController construction");
	}

	@Resource
	 PersonService ps; // ע�� service ��

	@RequestMapping(value = "/alltest", method = RequestMethod.GET)
	@ResponseBody
	public String getAllPersons() {
		return "Hello from Person Controller! This is the /person/all endpoint.";
	}

	@RequestMapping(value = "/person/all")
	 public String findAll(Map<String, Object> model)
	 { // ���� model ������������
		 System.out.println(" find All");
		 List<Person> personList = ps.findAll();
		 model.put("personList", personList);
		  return "person/jPersonList"; // ��ת�� jPersonList ҳ��
		 //return "person/test";  // ok
		 }

/*	@RequestMapping(value = "/all", method = RequestMethod.GET)
	public ModelAndView findAll() {
		System.out.println("find All");
		List<Person> personList = ps.findAll();

		ModelAndView mav = new ModelAndView("person/jPersonList");
		mav.addObject("personList", personList);
		return mav;
	}*/

	 @RequestMapping("/person/toCreatePersonInfo")
	 public String toCteatePersonInfo() { 
		 // ��ת����ҳ��
		 System.out.println("��ת����ҳ��");
		 return "/person/jPersonCreate";

	 }
	@RequestMapping("/person/toUpdatePersonInfo") 
	public String toUpdatePersonInfo(Integer id, Model model)
	{ // ��ת�޸�ҳ�� 
		Person p = ps.get(id); 
		// ���Ҫ�޸ĵļ�¼����������ҳ���ֵ
		model.addAttribute("p", p); // �����ݷŵ� response 
		return "/person/jPersonUpdate"; 
		
	}
	@RequestMapping("/person/updatePersonList")
	public String updatePersonList(Person p) { 
		if (p.getId() == null) {
			System.out.println("��������");
			ps.insert(p);
		// ���� Service �㷽������������
		} else { ps.update(p);
			System.out.println("��������");
		// ���� Service �㷽������������ 
		}
		return "redirect:/person/all.action"; // ת����Ա�б� action } 
		
		
	}


	@RequestMapping("/person/deleteById")
	public String deleteById(Integer id){
		ps.deleteById(id);
		return "redirect:/person/all.action"; // ת����Ա�б� action 
		}
	@RequestMapping("/person/deleteMuch")
	public String deleteMuch(@RequestParam("id")  Integer[] ids){ 
		// ����ɾ����¼
		System.out.println("����ɾ����¼");
		if(ids!=null)
			System.out.println("��¼"+ids.length);
		for (Integer delId : ids){
			System.out.println("ɾ����¼"+ delId);
			ps.deleteById(delId); }
		return "redirect:/person/all.action"; 
		// ת����Ա�б� action 
		}
	
	 }
