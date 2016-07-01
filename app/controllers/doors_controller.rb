class DoorsController < ApplicationController
	before_action :set_door
	before_action :has_door_access, :logged_in_user, only: [ :open_door, :close_door ]
	before_action :admin_user, :logged_in_user, except: [ :status, :open_door, :close_door ]
	# Allow access to function only to logged in users.

	# GET /users
	# GET /users.json
	def index
		@doors = Door.all
	end

	# GET /users/1
	# GET /users/1.json
	def show
	end

	# GET /users/new
	def new
		@door = Door.new
	end

	# GET /users/1/edit
	def edit
	end

	# POST /users
	# POST /users.json
	def create
		@door = Door.new(door_params)

		respond_to do |format|
			if @door.save
				format.html { redirect_to @door, notice: 'Door was successfully created.' }
			else
				format.html { render :new }
			end
		end
	end

	# PATCH/PUT /users/1
	# PATCH/PUT /users/1.json
	def update
		respond_to do |format|
			if @door.update(door_params)
				format.html { redirect_to @door, notice: 'Door was successfully updated.' }
			else
				format.html { render :edit }
			end
		end
	end

	# DELETE /users/1
	# DELETE /users/1.json
	def destroy
		@door.destroy
		respond_to do |format|
			format.html { redirect_to doors_url, notice: 'Door was successfully destroyed.' }
			format.json { head :no_content }
		end
	end


	# Open the door function
	def open_door
		# Get the status and just do the opposite action, it should go to true.
		@door.status = true
		# Save the new status
		@door.save!
		flash[:success] = "Door is open!"
		# Redirect to actions
		redirect_to root_url
	end

	def close_door
		# Close the door.
		@door.status = false
		# Save the state
		@door.save!
		flash[:danger] = "Door is closed!"
		# Go back to the homepage
		redirect_to root_url
	end

	def status
	end

	private
	# Select which door to open, this may be generalized for any door in the future.
	def set_door
		@door = Door.first
	end

end
