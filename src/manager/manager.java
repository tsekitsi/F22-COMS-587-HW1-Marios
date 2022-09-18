import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

public class manager {
    //public static int BEACON_LISTENER_PORT = 2345;

    public static Set<String> activeAgents = Collections.synchronizedSet(new HashSet<>()); // start with empty set.

    /**
     * Get the set of active agents.
     *
     * @return set of active agents
     */
    public Set<String> getAgents() {
        return activeAgents;
    }

    public static void main(String [] args) {
        int beaconPort = Integer.parseInt(args[0]);

        AgentMonitor aMonitor = new AgentMonitor(activeAgents);
        new BeaconListener(beaconPort).start();
    }
}
