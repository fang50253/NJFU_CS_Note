import java.io.File;

public class FilePair{
    private final File parent;
    private final File child;

    public FilePair(File parent,File child){
        this.parent=parent;
        this.child=child;
    }

    public File getParent(){
        return this.parent;
    }

    public File getChild(){
        return this.child;
    }
}