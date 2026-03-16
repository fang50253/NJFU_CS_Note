package edu.hdu.javaee.hibernate;

import java.util.Date;
import java.util.List;
import org.hibernate.HibernateException;
import org.hibernate.SessionFactory;
import org.hibernate.cfg.Configuration;
import org.hibernate.classic.Session;

public class Test {
    private static final SessionFactory sessionFactory;
    static {
        try {
            sessionFactory = new Configuration().configure().buildSessionFactory();
        } catch (Throwable ex) {
            System.err.println("Failed to create sessionFactory object." + ex);
            throw new ExceptionInInitializerError(ex);
        }
    }
    
    public static SessionFactory getSessionFactory(){
        return sessionFactory;
    }
    
    public static void main(String[] args) {
        BLOG blog=new BLOG();
        blog.setTitle("这是日志标题");
        blog.setContent("这是日志内容");
        blog.setDate(new Date());
        Test t=new Test();
        Session session=Test.getSessionFactory().getCurrentSession();
        session.beginTransaction();
        t.save(session,blog);
        t.select(session);
        //t.update(session,1); // 需要确保有对应ID的数据才能测试更新
        //t.select(session);
        //t.delete(session,1); // 需要确保有对应ID的数据才能测试删除
        //t.select(session);
        session.getTransaction().commit();
    }
    
    public void save(Session session,BLOG blog){
        try{
            session.save(blog);
        }
        catch (HibernateException e){
            e.printStackTrace();
        }
    }
    
    public void select(Session session){
        try{
            String sql="from BLOG";
            List list=session.createQuery(sql).list();
            for(Object obj : list){
                BLOG b=(BLOG)obj;
                System.out.println(b.getId());
                System.out.println(b.getTitle());
                System.out.println(b.getContent());
                System.out.println(b.getDate());
            }
        }
        catch (HibernateException e){
            e.printStackTrace();
        }
    }
    
    public void update(Session session,Integer id){
        try{
            BLOG blog=(BLOG)session.get(BLOG.class,id);
            blog.setTitle("更新后的标题");
            session.update(blog);
        }
        catch(HibernateException e){
            e.printStackTrace();
        }
    }
    
    public void delete(Session session,Integer id){
        try{
            BLOG blog=(BLOG)session.get(BLOG.class,id);
            session.delete(blog);
        }
        catch(HibernateException e){
            e.printStackTrace();
        }
    }
}