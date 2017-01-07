<?php

namespace App\Http\Controllers;


use App\CustomerClient;
use App\VehicleCustomerTransaction;


class TransactionsController extends Controller {
	/*
	|--------------------------------------------------------------------------
	| Create a new transaction
	|--------------------------------------------------------------------------
	|
	| New transactions to be valid require the amount transferred to be strictly
	| positive, the customer and vehicle to exist and the customer to have
	| credit equal to or greater than the amoutn transferred
	|
	*/
	public function transaction_request ($from, $to, $amount) {
		if (VehicleController::validate_authorization($to)) { // if authorized
			$customer = CustomerClient::find($from);
			if ((($amount > 0) && $customer && ($customer->credit >= $amount))) {
				// create new transaction object
				$transaction                     = new VehicleCustomerTransaction();
				$transaction->amount_nis         = $amount;
				$transaction->vehicle_client_id  = $to;
				$transaction->customer_client_id = $from;

				// apply the transaction between customer and vehicle
				VehicleController::deposit_money($to, $amount);
				CustomerController::withdraw_money($from, $amount);
				// save the transaction
				$transaction->save();

				return response()->json(True, 200);
			}
		}

		return response()->json(Null, 200);
	}

	public function index () {
		return response()->json(VehicleCustomerTransaction::all());
	}
}
