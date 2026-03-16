package cn.wmyskxz.controller;

//import javax.annotation.Resource;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;

import cn.wmyskxz.entity.User;
import cn.wmyskxz.service.UserService;
import org.springframework.web.bind.annotation.RequestParam;

import java.util.ArrayList;
import java.util.List;

@Controller
@RequestMapping("/user")
public class UserController {

    //@Resource
    @Autowired
    private UserService userService;

    @RequestMapping("/findUser")
    public String findUser(Model model) {
        int id = 1;
        User user = this.userService.findUserById(id);
        model.addAttribute("user", user);
        return "index";
    }

    @RequestMapping("/getAllUser")
    public String getAllUser(Model model) {
        System.out.println("getAllUser contronller ...getAllUser");
        List<User>  userlist= this.userService.getAllUser();
        if(userlist!=null)
            System.out.println("userlist...length"+userlist.size());
        else
            System.out.println("userlist...length 0");
        model.addAttribute("userlist", userlist);

        return "alluser";
    }


    @RequestMapping("/toCreatUser")
    public String toCreatUser() {
        System.out.println("跳转新增页面");
        return "/jUserCreate";
    }
    @RequestMapping("/toUpdateUserInfo")
    public String toUpdatePersonInfo(Integer id, Model model)
    { // 跳转修改页面
        User p=userService.findUserById(id);
        // 获得要修改的记录，重新设置页面的值
        model.addAttribute("p", p); // 将数据放到 response
        return "/jUserCreate";

    }

    @RequestMapping("/updateUser")
    public String addUser(User p) {

        if (p.getId() == null) {
            System.out.println("插入数据"+p.getUsername());
            this.userService.addUser(p);
            // 调用 Service 层方法，插入数据
        } else {
            userService.updateUser(p);
            System.out.println("更新数据");
            // 调用 Service 层方法，更新数据
        }

        return "redirect:/user/getAllUser";
    }


    @RequestMapping("/deleteById")
    public String deleteById(Integer id){
        System.out.println("删除数据id"+id);
        userService.deleteById(id);
        return "redirect:/user/getAllUser"; // 转向书籍列表 action
    }

    @RequestMapping("/deleteMuch")
    public String deleteMuch(@RequestParam("id")  Integer[] ids){
        // 批量删除记录
        System.out.println("批量删除记录");
        if(ids!=null)
        {
            System.out.println("记录"+ids.length);
            List<String> list=new ArrayList<String>();
            for (Integer id :ids)
                list.add(id.intValue()+"");

            userService.deleteMuchByIds(list);
        }
        /*for (Integer delId : ids){
            System.out.println("删除记录"+ delId);
            ps.deleteById(delId); }*/




        return "redirect:/user/getAllUser";
        // 转向书籍列表 action
    }
}
