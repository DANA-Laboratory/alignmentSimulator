// file "create1.java" when compiled yields "create1.class" 
import vrml.*;
import vrml.field.*;
import vrml.node.*;

public class create1 extends Script
{
    private SFNode the_parent;
    private Browser b;
    private BaseNode vrml_box [];

    public void initialize()
    {
        // get hold of the node reference
        the_parent = (SFNode) getField("parentNode");
        b = getBrowser();
    }

    public void processEvent(Event e)
    {
       // now in response to some input we want to create the new box:
       createNode();
    }

    private void createNode()
    {
        String green_box =
           "Shape { " +
            "appearance Appearance { " +
              "material Material { " +
                "emissiveColor 0 1 0 " +
              "} " +   
            "} " +
            "geometry Box {} " +
          "}";

        try
          {vrml_box = b.createVrmlFromString(green_box);}
        catch(vrml.InvalidVRMLSyntaxException theError)
	  {System.out.println("caught exception");}

        System.out.println(green_box);
        // Now we need to add it to the existing scene.
        // first need to get the eventIn of the Group
        MFNode add_kids = (MFNode) ( (Node) the_parent.getValue() ).getEventIn("addChildren");

        // now we can add this to the Node directly
        add_kids.setValue(vrml_box);
    }
}