package cn.wmyskxz.entity;

public class User {
	//private int id;
	/*//public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}*/
	private Integer id;
	public Integer getId() {
		return id;
	}

	public void setId(Integer id) {
		this.id = id;
	}
	public String getUsername() {
		return username;
	}
	public void setUsername(String username) {
		this.username = username;
	}
	private String username;

	private String isbn;
	public String getIsbn() {
		return isbn;
	}
	public void setIsbn(String isbn) {
		this.isbn = isbn;
	}
	private String author;
	public void setAuthor(String author) {
		this.author = author;
	}
	public String getAuthor() {
		return author;
	}
	@Override
	public String toString() {
		return "User{" +
				"id=" + id +
				", username='" + username + '\'' +
				", isbn='" + isbn + '\'' +
				", author='" + author + '\'' +
				'}';
	}


}