package spring.mvc.service;
import java.util.*;

import org.springframework.stereotype.Service;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import java.util.*;
import spring.mvc.bean.*;
@Service 
public class PersonService { 
	// ģ���ڴ����ݿ⣬׼������ // ����һ������
	 private static Map<Integer,Person> map = new HashMap<Integer,Person>();
	// ��ʼ�� id 
	 private static Integer id = 0; 
	// ���þ�̬���ʼ������ 
	 static { for (int i = 0; i < 10; i++) {
		 Person p = new Person(); p.setId(id++); p.setName("Charie" + i); p.setAge(10 + i); map.put(i, p);
	 } }

	public PersonService() {
		 System.out.println("person service construction");
	}

	public List<Person> findAll() {
			// �� map ����ת��Ϊ list ���
			return new ArrayList(map.values());  // ���һ�� Person ���� 
		}
			public Person get(Integer id) { return map.get(id); } 
			// ������Ա��Ϣ
			 public void insert(Person p) { id++; p.setId(id); map.put(id, p); } 
			// �޸���Ա��Ϣ
			 public void update(Person p){map.put(p.getId(), p); } 
			// ɾ��������¼ 
			public void deleteById(Integer id) {map.remove(id); }
			
			@RequestMapping("/person/deleteMuch") 
			public String deleteMuch(@RequestParam("id") Integer[] ids){
				// ����ɾ����¼
				for (Integer delId : ids){ 
					//ps.deleteById(delId);
					}
				return "redirect:/person/all.action"; // ת����Ա�б� action }
			}
		}
