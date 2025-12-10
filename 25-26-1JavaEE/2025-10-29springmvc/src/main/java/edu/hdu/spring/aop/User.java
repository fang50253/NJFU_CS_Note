package edu.hdu.spring.aop;
public class User {
    private int id;
	private String name;
	private String cardID;
	public int getId() {
        return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getCardID() {
		return cardID;
	}
	public void setCardID(String cardID) {
		this.cardID = cardID;
	}
	public String toString() {
	    return "[ name =" + name + ", carID = " + cardID + ", id = " + id +  " ]";
	}
}
