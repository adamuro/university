import java.util.HashMap;

public class State {
    public class CashMachine {
        public ICashMachineState state;
        public String authorizedClient;
        public HashMap<String, Double> clientAccounts;

        public CashMachine() {
            this.state = new FreeCashMachineState(this);
            this.clientAccounts = new HashMap<>();
        }

        public void setState (ICashMachineState newState) {
            this.state = newState;
        }

        public void startPayment() throws Exception {
            this.state.startPayment();
        }

        public void authorize(String client) throws Exception {
            this.state.authorize(client);
        }

        public void depositCash(Double value) throws Exception {
            this.state.depositCash(value);
        }

        public void withdrawCash(Double value) throws Exception {
            this.state.withdrawCash(value);
        }

        public void endPayment() throws Exception {
            this.state.endPayment();
        }
    }

    public interface ICashMachineState {
        void startPayment() throws Exception;
        void authorize(String client) throws Exception;
        void depositCash(Double value) throws Exception;
        void withdrawCash(Double value) throws Exception;
        void endPayment() throws Exception;
    }

    public class FreeCashMachineState implements ICashMachineState {
        private CashMachine cashMachine;

        public FreeCashMachineState(CashMachine cashMachine) {
            this.cashMachine = cashMachine;
        }

        @Override
        public void startPayment() {
            this.cashMachine.setState(new UnauthorizedCashMachineState(this.cashMachine));
        }

        @Override
        public void authorize(String client) throws Exception {
            throw new Exception();
        }

        @Override
        public void depositCash(Double value) throws Exception {
            throw new Exception();
        }

        @Override
        public void withdrawCash(Double value) throws Exception {
            throw new Exception();
        }

        @Override
        public void endPayment() throws Exception {
            throw new Exception();
        }
    }

    public class UnauthorizedCashMachineState implements ICashMachineState {
        private CashMachine cashMachine;

        public UnauthorizedCashMachineState(CashMachine cashMachine) {
            this.cashMachine = cashMachine;
        }

        @Override
        public void startPayment() throws Exception {
            throw new Exception();
        }

        @Override
        public void authorize(String client) {
            this.cashMachine.setState(new AuthorizedCashMachineState(this.cashMachine));
            this.cashMachine.authorizedClient = client;
            if(!this.cashMachine.clientAccounts.containsKey(client)) {
                this.cashMachine.clientAccounts.put(client, 0.00);
            }
        }

        @Override
        public void depositCash(Double value) throws Exception {
            throw new Exception();
        }

        @Override
        public void withdrawCash(Double value) throws Exception {
            throw new Exception();
        }

        @Override
        public void endPayment() throws Exception {
            throw new Exception();
        }
    }

    public class AuthorizedCashMachineState implements ICashMachineState {
        private CashMachine cashMachine;

        public AuthorizedCashMachineState(CashMachine cashMachine) {
            this.cashMachine = cashMachine;
        }

        @Override
        public void startPayment() throws Exception {
            throw new Exception();
        }

        @Override
        public void authorize(String client) throws Exception {
            throw new Exception();
        }

        @Override
        public void depositCash(Double value) {
            String client = this.cashMachine.authorizedClient;
            Double accountBalance  = this.cashMachine.clientAccounts.get(client);
            this.cashMachine.clientAccounts.replace(client, accountBalance + value);
        }

        @Override
        public void withdrawCash(Double value) throws Exception {
            String client = this.cashMachine.authorizedClient;
            Double accountBalance  = this.cashMachine.clientAccounts.get(client);
            if(accountBalance - value < 0) {
                throw new Exception();
            }

            this.cashMachine.clientAccounts.replace(client, accountBalance - value);
        }

        @Override
        public void endPayment() {
            this.cashMachine.setState(new FreeCashMachineState(this.cashMachine));
            this.cashMachine.authorizedClient = null;
        }
    }
}
