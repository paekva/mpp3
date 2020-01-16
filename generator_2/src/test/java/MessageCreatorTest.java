import org.junit.Test;
import types.EType;

import static org.junit.Assert.*;

public class MessageCreatorTest {
    private static MessageCreator messageCreator = new MessageCreator();

    @Test
    public void testGetFibonacciMessage() {
        EType messageType = EType.FIBONACCI;
        int value = 8;
        TMessage.TMessageProto msg = messageCreator.getMessage(messageType, value);
        assertTrue(msg.getType() == messageType.index() && msg.getData(0) == value);
    }

    @Test
    public void testGetPowMessage() {
        EType messageType = EType.POW;
        int base = 8;
        int value = 8;
        TMessage.TMessageProto msg = messageCreator.getMessage(messageType, base, value);
        assertTrue(msg.getType() == messageType.index()
                && msg.getData(0) == base
                && msg.getData(1) == value);
    }

    @Test
    public void testGetBubbleSortMessage() {
        EType messageType = EType.BUBBLE_SORT_UINT64;
        int size = 3;
        double[] array = new double[]{1, 9 ,0};
        TMessage.TMessageProto msg = messageCreator.getMessage(messageType, size, array);
        assertTrue(msg.getType() == messageType.index()
                && msg.getData(0) == size);
        for(int i =0; i< size; i++){
            assertTrue(msg.getData(i+1) == array[i]);
        }
    }

    @Test
    public void testGetStopMessage() {
        EType messageType = EType.STOP;
        TMessage.TMessageProto msg = messageCreator.getMessage(messageType);
        assertTrue(msg.getType() == messageType.index());
    }
}