# Define roles, user and IP address of deployment server
# role :name, %{[user]@[IP adde.]}
# role :app, %w{deployer@workshops.utep.edu}
# role :web, %w{deployer@workshops.utep.edu}
# role :db,  %w{deployer@workshops.utep.edu}

role :app, %w{deployer@workshops.utep.edu}
role :web, %w{deployer@workshops.utep.edu}
role :db,  %w{deployer@workshops.utep.edu}

# Define server(s)
server 'workshops.utep.edu', user: 'deployer', roles: %w{web}

set :deploy_to, "/var/sentora/hostdata/at/public_html/skunkworks_at_utep_edu/skunk"
set :stage, :production

#Stop deletion of the public uploads
set :linked_dirs, fetch(:linked_dirs) + %w{public/system public/uploads}

# SSH Options
# See the example commented out section in the file
# for more options.
set :ssh_options, {
		forward_agent: false,
		auth_methods: %w(password),
		password: 'Ttnkf@g2011!',
		user: 'deployer',
}
