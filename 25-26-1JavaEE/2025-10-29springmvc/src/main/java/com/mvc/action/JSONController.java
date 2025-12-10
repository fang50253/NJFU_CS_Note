package com.mvc.action;

import java.util.HashMap;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

import com.mvc.bean.Shop;
@Controller
@RequestMapping("/kfc/brands")
public class JSONController {

    public JSONController() {

        System.out.println(" JSONController construction!");
    }

    @RequestMapping(value = "{name}", method = RequestMethod.GET)
	public @ResponseBody
	Shop getShopInJSON(@PathVariable String name) {

		Shop shop = new Shop();
		shop.setName(name);
		shop.setStaffName(new String[] { "mkyong1", "mkyong2" });

		return shop;

	}
	
    @RequestMapping(value = "/n", method = { RequestMethod.GET })  
    @ResponseBody  
    public Map testJson(HttpServletRequest request, HttpServletResponse arg1)  
            throws Exception {  
        // TODO Auto-generated method stub  
        Map map = new HashMap();  
        map.put("status", "����");  
        map.put("info", "hello����");  
        return map;  
    }  

}