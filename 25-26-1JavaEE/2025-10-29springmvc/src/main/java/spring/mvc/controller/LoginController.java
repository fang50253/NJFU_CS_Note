package spring.mvc.controller;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import spring.mvc.bean.Person;
import spring.mvc.bean.Student;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

@Controller
public class LoginController {
    public LoginController() {
        System.out.println("Logincontroller construction");
    }

    @RequestMapping("/login")
    public String sign(String stuid, String stuName, Model model, HttpServletRequest request) { // 跳转修改页面
        System.out.println("stuid " + stuid + "  stuName..." + stuName);
     /*  if((stuid!=null)&&(stuName!=null))
       {
           model.addAttribute("stuName", stuName);
           return "success";
       }
       else
           return "fail";

    }*/

        ServletContext context = request.getSession().getServletContext();

        String IP = request.getRemoteAddr();
        SimpleDateFormat format = new SimpleDateFormat("yyyy-M-dd hh:mm:ss");
        String loginTime = format.format(new java.util.Date());
        boolean idflag = false, ipflag = false;

        //PrintWriter out=response.getWriter();
        if (((stuid != null) && (stuid.length() > 0)) && ((stuName != null) && (stuName.length() > 0))) {
            Student stu = new Student(stuid, stuName);
            synchronized (this) {
                Map<String, Student> idlist = (HashMap<String, Student>) (context.getAttribute("idlist"));
                ArrayList<String> iplist = (ArrayList<String>) (context.getAttribute("iplist"));
                if (idlist == null) {
                    idlist = new HashMap<String, Student>();//记录历史签到id
                    iplist = new ArrayList<String>();//记录历史签到ip
                    idlist.put(stuid, stu);
                    iplist.add(IP);
                    context.setAttribute("idlist", idlist);
                    context.setAttribute("iplist", iplist);
                } else {
                    if ((!idlist.containsKey(stuid)) && (!iplist.contains(IP))) {
                        idlist.put(stuid, stu);
                        iplist.add(IP);
                        System.out.println("stuid" + stuid + " stuname" + stuName + " ip" + IP + "The current sign-in is successful ");
                    } else if ((idlist.containsKey(stuid)) && (iplist.contains(IP))) {
                        idflag = true;
                        ipflag = true;
                    } else if (idlist.containsKey(stuid)) {
                        idflag = true;
                        System.out.println("Do not repeat the check-in");
                        //this.message = "Do not repeat the check-in";
                        model.addAttribute("message", stuName + " Do not repeat the check-in");
                    } else if (iplist.contains(IP)) {
                        ipflag = true;
                        System.out.println("Only the same machine can sign one name");
                        // this.message ="Only the same machine can sign one name";
                        model.addAttribute("message", stuName + " Only the same machine can sign one name");

                    }


                }

                if ((!idflag) && (!ipflag)) {
                    System.out.println("The current sign-in is successful<p>");
                    //this.message ="The current sign-in is successful<p>";
                    model.addAttribute("message", stuName + " The current sign-in is successful<p>");
                   // model.addAttribute("idlist", idlist);
                    if (idlist != null) {
                        System.out.println("The current sign-in is successful！" + idlist.size() + " 人<p>");
                        ArrayList studentlist=new ArrayList();
                        for (String key : idlist.keySet()) {
                            System.out.print("stuid:" + key);
                            System.out.println(" stuName " + idlist.get(key).getName() + "<br>");
                            studentlist.add(idlist.get(key));

                        }
                        model.addAttribute("studentlist", studentlist);
                    }
                } else if (idflag) {
                    System.out.println("Do not repeat the check-in");
                    //this.message = "Do not repeat the check-in";
                    model.addAttribute("message", stuName + " Do not repeat the check-in");
                } else if (ipflag) {
                    System.out.println("Only the same machine can sign one name");
                    // this.message ="Only the same machine can sign one name";
                    model.addAttribute("message", stuName + " Only the same machine can sign one name");
                }
                // System.out.close();
            }

            return "success";
        } else {
            System.out.println("The check-in content is incomplete");
            // this.message ="The check-in content is incomplete"; //"签到内容不全！";
            model.addAttribute("message", stuName + " The check-in content is incomplete");
            return "fail";
        }
    }
}
