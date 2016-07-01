Rails.application.routes.draw do
	resources :users

	root 'pages#index'
	get 'opening' => 'pages#opening_door'

	# Sessions
	get 'login' => 'sessions#new'
	get 'create_session' => 'sessions#create'
	delete 'logout' => 'sessions#destroy'

	# Door functions
	get 'open_door' => 'doors#open_door'
	# Close the door
	get 'close_door' => 'doors#close_door'
	get 'opening_door' => 'pages#opening_door', as: 'opening_path'


	# Door Routes
	resources :doors do
		member do
			get :status
		end
	end

	# Error Path
	get 'no_access' => 'pages#no_access', as: 'no_access'

end
