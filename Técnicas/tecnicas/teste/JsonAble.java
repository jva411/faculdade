package tecnicas.teste;

import java.util.HashMap;

java.lang.reflect.*;

public interface JsonAble{

    public String toJSON(){
        StringBuilder sb = new StringBuilder("{\n");

        HashMap<String, Object> values = new HashMap<>();;

        return sb.append('}').toString();
    }
    
    private void runByHierarque(HashMap<String, Object> map, Class Class){
        if(!Class.getAnnotatedSuperclass().getType().getTypeName().equals("java.lang.Object")) runByHierarque(map, Class.getAnnotatedSuperclass().getClass());
        for(Field F:Class.getFields()){
            
        }
    }

}