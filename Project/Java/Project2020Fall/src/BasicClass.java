import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class BasicClass implements Comparable<BasicClass> {
    private int property1;
    private int property2;
    private final List<BasicClass> children;

    public BasicClass() {
        this.property1 = 0;
        this.property2 = 0;
        this.children = new ArrayList<BasicClass>();
    }

    public boolean addChild(BasicClass newChild) {
        for (BasicClass child : this.children) {
            if (child == newChild || child.equals(newChild) == true) {
                return false;
            }
        }
        this.children.add(newChild);
        return true;
    }

    public int getProperty1() {
        return this.property1;
    }

    public int getProperty2() {
        return this.property2;
    }

    public List<BasicClass> getChildren() {
        return this.children;
    }

    public void setProperty1(int property1) {
        this.property1 = property1;
    }

    public void setProperty2(int property2) {
        this.property2 = property2;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null || !(obj instanceof BasicClass)) {
            return false;
        }
        BasicClass bcObj = (BasicClass) obj;
        if (bcObj.getProperty1() == this.property1 && bcObj.getProperty2() == this.property2) {
            return this.compareTo(bcObj) == 0 ? true : false;
        }
        return false;
    }

    @Override
    public int compareTo(BasicClass other) {
        if (this.property1 == other.property1) {
            if (this.property2 == other.property2) {
                List<BasicClass> thisList = this.getChildren();
                List<BasicClass> otherList = other.getChildren();
                if (thisList.size() != otherList.size()) {
                    return thisList.size() - otherList.size();
                }
                Collections.sort(thisList);
                Collections.sort(otherList);
                for (int i = 0; i < thisList.size(); ++i) {
                    
                }
            }
            return ((Integer)this.property2).compareTo(((Integer)other.getProperty2()));
        }
        return ((Integer)this.property1).compareTo(((Integer)other.getProperty1()));
    }
}
