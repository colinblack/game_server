package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class User
	{
		public static const PROTO:String = "User.User";
		public var package_root:*;
		public  var message:*;
		public var base:Base;
		public var ts:int;
		public var activity:Activity;
		public var notifies:NotifyItemCPPAll;
		public var charges:AccumulateCharge;
		public var gameactivity:GameAcitivityAllCPP;
		public var item:Vector.<PropsItemCPP>;
		public var builds:Vector.<BuildingCPP>;
		public var cropland:Vector.<CropLandCPP>;
		public var equipments:Vector.<ProduceEquipCPP>;
		public var animals:Vector.<AnimalCPP>;
		public var equipmentstars:Vector.<EquipmentStarCPP>;
		public var fruits:Vector.<FruitCPP>;
		public var orders:Vector.<OrderCPP>;
		public var truck:TruckCPP;
		public var shipping:ShippingCPP;
		public var shipboxes:Vector.<ShippingBoxCPP>;
		public var npcseller:NPCSellerCPP;
		public var opents:int;
		public var hasNewDyInfo:Boolean;
		public var theme:ThemeInfoResp;
		public var hasNewMsgInfo:Boolean;
		public var pet:Vector.<UnlockPetCPP>;
		public function User(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			base = undefined;
			ts = undefined;
			activity = undefined;
			notifies = undefined;
			charges = undefined;
			gameactivity = undefined;
			item = new Vector.<PropsItemCPP>();
			builds = new Vector.<BuildingCPP>();
			cropland = new Vector.<CropLandCPP>();
			equipments = new Vector.<ProduceEquipCPP>();
			animals = new Vector.<AnimalCPP>();
			equipmentstars = new Vector.<EquipmentStarCPP>();
			fruits = new Vector.<FruitCPP>();
			orders = new Vector.<OrderCPP>();
			truck = undefined;
			shipping = undefined;
			shipboxes = new Vector.<ShippingBoxCPP>();
			npcseller = undefined;
			opents = undefined;
			hasNewDyInfo = undefined;
			theme = undefined;
			hasNewMsgInfo = undefined;
			pet = new Vector.<UnlockPetCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.base = this.base.serialize();
			serializeObj.ts = this.ts;
			serializeObj.activity = this.activity.serialize();
			if(this.notifies!= undefined)
			{
				serializeObj.notifies = this.notifies.serialize();
			}
			serializeObj.charges = this.charges.serialize();
			serializeObj.gameactivity = this.gameactivity.serialize();
			serializeObj.item = [];
			for(var i:int = 0;i < this.item.length;i++)
			{
				serializeObj.item.push(this.item[i].serialize());
			}
			serializeObj.builds = [];
			for(var i:int = 0;i < this.builds.length;i++)
			{
				serializeObj.builds.push(this.builds[i].serialize());
			}
			serializeObj.cropland = [];
			for(var i:int = 0;i < this.cropland.length;i++)
			{
				serializeObj.cropland.push(this.cropland[i].serialize());
			}
			serializeObj.equipments = [];
			for(var i:int = 0;i < this.equipments.length;i++)
			{
				serializeObj.equipments.push(this.equipments[i].serialize());
			}
			serializeObj.animals = [];
			for(var i:int = 0;i < this.animals.length;i++)
			{
				serializeObj.animals.push(this.animals[i].serialize());
			}
			serializeObj.equipmentstars = [];
			for(var i:int = 0;i < this.equipmentstars.length;i++)
			{
				serializeObj.equipmentstars.push(this.equipmentstars[i].serialize());
			}
			serializeObj.fruits = [];
			for(var i:int = 0;i < this.fruits.length;i++)
			{
				serializeObj.fruits.push(this.fruits[i].serialize());
			}
			serializeObj.orders = [];
			for(var i:int = 0;i < this.orders.length;i++)
			{
				serializeObj.orders.push(this.orders[i].serialize());
			}
			if(this.truck!= undefined)
			{
				serializeObj.truck = this.truck.serialize();
			}
			if(this.shipping!= undefined)
			{
				serializeObj.shipping = this.shipping.serialize();
			}
			serializeObj.shipboxes = [];
			for(var i:int = 0;i < this.shipboxes.length;i++)
			{
				serializeObj.shipboxes.push(this.shipboxes[i].serialize());
			}
			serializeObj.npcseller = this.npcseller.serialize();
			serializeObj.opents = this.opents;
			if(this.hasNewDyInfo!= undefined)
			{
				serializeObj.hasNewDyInfo = this.hasNewDyInfo;
			}
			if(this.theme!= undefined)
			{
				serializeObj.theme = this.theme.serialize();
			}
			if(this.hasNewMsgInfo!= undefined)
			{
				serializeObj.hasNewMsgInfo = this.hasNewMsgInfo;
			}
			serializeObj.pet = [];
			for(var i:int = 0;i < this.pet.length;i++)
			{
				serializeObj.pet.push(this.pet[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):User
		{
			base = undefined;
			ts = undefined;
			activity = undefined;
			notifies = undefined;
			charges = undefined;
			gameactivity = undefined;
			item = new Vector.<PropsItemCPP>();
			builds = new Vector.<BuildingCPP>();
			cropland = new Vector.<CropLandCPP>();
			equipments = new Vector.<ProduceEquipCPP>();
			animals = new Vector.<AnimalCPP>();
			equipmentstars = new Vector.<EquipmentStarCPP>();
			fruits = new Vector.<FruitCPP>();
			orders = new Vector.<OrderCPP>();
			truck = undefined;
			shipping = undefined;
			shipboxes = new Vector.<ShippingBoxCPP>();
			npcseller = undefined;
			opents = undefined;
			hasNewDyInfo = undefined;
			theme = undefined;
			hasNewMsgInfo = undefined;
			pet = new Vector.<UnlockPetCPP>();
			this.base = new Base(package_root).unserialize(msgObj.base);
			this.ts = msgObj.ts;
			this.activity = new Activity(package_root).unserialize(msgObj.activity);
			if(msgObj.hasOwnProperty("notifies"))
			{
				this.notifies = new NotifyItemCPPAll(package_root).unserialize(msgObj.notifies);
			}
			this.charges = new AccumulateCharge(package_root).unserialize(msgObj.charges);
			this.gameactivity = new GameAcitivityAllCPP(package_root).unserialize(msgObj.gameactivity);
			for(var i:int = 0;i < msgObj.item.length;i++)
			{
				this.item.push(new PropsItemCPP(package_root).unserialize(msgObj.item[i]));
			}
			for(var i:int = 0;i < msgObj.builds.length;i++)
			{
				this.builds.push(new BuildingCPP(package_root).unserialize(msgObj.builds[i]));
			}
			for(var i:int = 0;i < msgObj.cropland.length;i++)
			{
				this.cropland.push(new CropLandCPP(package_root).unserialize(msgObj.cropland[i]));
			}
			for(var i:int = 0;i < msgObj.equipments.length;i++)
			{
				this.equipments.push(new ProduceEquipCPP(package_root).unserialize(msgObj.equipments[i]));
			}
			for(var i:int = 0;i < msgObj.animals.length;i++)
			{
				this.animals.push(new AnimalCPP(package_root).unserialize(msgObj.animals[i]));
			}
			for(var i:int = 0;i < msgObj.equipmentstars.length;i++)
			{
				this.equipmentstars.push(new EquipmentStarCPP(package_root).unserialize(msgObj.equipmentstars[i]));
			}
			for(var i:int = 0;i < msgObj.fruits.length;i++)
			{
				this.fruits.push(new FruitCPP(package_root).unserialize(msgObj.fruits[i]));
			}
			for(var i:int = 0;i < msgObj.orders.length;i++)
			{
				this.orders.push(new OrderCPP(package_root).unserialize(msgObj.orders[i]));
			}
			if(msgObj.hasOwnProperty("truck"))
			{
				this.truck = new TruckCPP(package_root).unserialize(msgObj.truck);
			}
			if(msgObj.hasOwnProperty("shipping"))
			{
				this.shipping = new ShippingCPP(package_root).unserialize(msgObj.shipping);
			}
			for(var i:int = 0;i < msgObj.shipboxes.length;i++)
			{
				this.shipboxes.push(new ShippingBoxCPP(package_root).unserialize(msgObj.shipboxes[i]));
			}
			this.npcseller = new NPCSellerCPP(package_root).unserialize(msgObj.npcseller);
			this.opents = msgObj.opents;
			if(msgObj.hasOwnProperty("hasNewDyInfo"))
			{
				this.hasNewDyInfo = msgObj.hasNewDyInfo;
			}
			if(msgObj.hasOwnProperty("theme"))
			{
				this.theme = new ThemeInfoResp(package_root).unserialize(msgObj.theme);
			}
			if(msgObj.hasOwnProperty("hasNewMsgInfo"))
			{
				this.hasNewMsgInfo = msgObj.hasNewMsgInfo;
			}
			for(var i:int = 0;i < msgObj.pet.length;i++)
			{
				this.pet.push(new UnlockPetCPP(package_root).unserialize(msgObj.pet[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):User
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}