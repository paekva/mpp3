package generators;

import org.junit.Test;
import types.EType;
import static org.junit.Assert.*;
import java.util.Arrays;

public class GeneratorTest {
    @Test
    public void getMessageTypeFromUniformDistribution() {
        double[] params = new double[]{1, 4};
        Uniform uniform = new Uniform(params);

        EType result = uniform.getMessageType();
        assertTrue(Arrays.asList(EType.values()).contains(result));
    }

    @Test
    public void getMessageTypeFromNormalDistribution() {
        double[] params = new double[]{1, 4};
        Normal normal = new Normal(params);

        EType result = normal.getMessageType();
        assertTrue(Arrays.asList(EType.values()).contains(result));
    }

    @Test
    public void getMessageTypeFromExponentialDistribution() {
        double[] params = new double[]{1, 4};
        Exponential exponential = new Exponential(params);

        EType result = exponential.getMessageType();
        assertTrue(Arrays.asList(EType.values()).contains(result));
    }

    @Test
    public void getFibbonachiNumber() {
    }

    @Test
    public void getArraySize() {
    }

    @Test
    public void getMessagesCount() {
    }
}