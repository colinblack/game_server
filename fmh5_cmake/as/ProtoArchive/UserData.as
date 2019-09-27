package com.sanguo.game.server.connectlogic.common.message.ProtoArchive
{
	import laya.utils.Byte;
	public class UserData
	{
		public static const PROTO:String = "ProtoArchive.UserData";
		public var package_root:*;
		public  var message:*;
		public var base:Base;
		public var charges:Vector.<ChargeItem>;
		public var builds:Vector.<BuildingsCPP>;
		public var equipstar:Vector.<EquipmentStarCPP>;
		public var cropland:Vector.<CropLandCPP>;
		public var equipments:Vector.<ProduceEquipCPP>;
		public var fruits:Vector.<FruitCPP>;
		public var item:Vector.<PropsItemCPP>;
		public var animals:Vector.<AnimalCPP>;
		public var orders:Vector.<OrderCPP>;
		public var truck:TruckCPP;
		public var shipping:ShippingCPP;
		public var shipboxes:Vector.<ShippingBoxCPP>;
		public var shop:Vector.<ShopCPP>;
		public var task:Vector.<TaskCPP>;
		public var mission:Vector.<MissionCPP>;
		public var activity:Vector.<ActivityCPP>;
		public var maildog:Vector.<MaidDogCPP>;
		public var friendlytree:Vector.<FriendlyTreeBasicCPP>;
		public var shopsellcoin:Vector.<ShopSellCoinCPP>;
		public var friendworker:Vector.<FriendWorkerCPP>;
		public var pet:Vector.<UnlockPetCPP>;
		public function UserData(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			base = undefined;
			charges = new Vector.<ChargeItem>();
			builds = new Vector.<BuildingsCPP>();
			equipstar = new Vector.<EquipmentStarCPP>();
			cropland = new Vector.<CropLandCPP>();
			equipments = new Vector.<ProduceEquipCPP>();
			fruits = new Vector.<FruitCPP>();
			item = new Vector.<PropsItemCPP>();
			animals = new Vector.<AnimalCPP>();
			orders = new Vector.<OrderCPP>();
			truck = undefined;
			shipping = undefined;
			shipboxes = new Vector.<ShippingBoxCPP>();
			shop = new Vector.<ShopCPP>();
			task = new Vector.<TaskCPP>();
			mission = new Vector.<MissionCPP>();
			activity = new Vector.<ActivityCPP>();
			maildog = new Vector.<MaidDogCPP>();
			friendlytree = new Vector.<FriendlyTreeBasicCPP>();
			shopsellcoin = new Vector.<ShopSellCoinCPP>();
			friendworker = new Vector.<FriendWorkerCPP>();
			pet = new Vector.<UnlockPetCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.base!= undefined)
			{
				serializeObj.base = this.base.serialize();
			}
			serializeObj.charges = [];
			for(var i:int = 0;i < this.charges.length;i++)
			{
				serializeObj.charges.push(this.charges[i].serialize());
			}
			serializeObj.builds = [];
			for(var i:int = 0;i < this.builds.length;i++)
			{
				serializeObj.builds.push(this.builds[i].serialize());
			}
			serializeObj.equipstar = [];
			for(var i:int = 0;i < this.equipstar.length;i++)
			{
				serializeObj.equipstar.push(this.equipstar[i].serialize());
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
			serializeObj.fruits = [];
			for(var i:int = 0;i < this.fruits.length;i++)
			{
				serializeObj.fruits.push(this.fruits[i].serialize());
			}
			serializeObj.item = [];
			for(var i:int = 0;i < this.item.length;i++)
			{
				serializeObj.item.push(this.item[i].serialize());
			}
			serializeObj.animals = [];
			for(var i:int = 0;i < this.animals.length;i++)
			{
				serializeObj.animals.push(this.animals[i].serialize());
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
			serializeObj.shop = [];
			for(var i:int = 0;i < this.shop.length;i++)
			{
				serializeObj.shop.push(this.shop[i].serialize());
			}
			serializeObj.task = [];
			for(var i:int = 0;i < this.task.length;i++)
			{
				serializeObj.task.push(this.task[i].serialize());
			}
			serializeObj.mission = [];
			for(var i:int = 0;i < this.mission.length;i++)
			{
				serializeObj.mission.push(this.mission[i].serialize());
			}
			serializeObj.activity = [];
			for(var i:int = 0;i < this.activity.length;i++)
			{
				serializeObj.activity.push(this.activity[i].serialize());
			}
			serializeObj.maildog = [];
			for(var i:int = 0;i < this.maildog.length;i++)
			{
				serializeObj.maildog.push(this.maildog[i].serialize());
			}
			serializeObj.friendlytree = [];
			for(var i:int = 0;i < this.friendlytree.length;i++)
			{
				serializeObj.friendlytree.push(this.friendlytree[i].serialize());
			}
			serializeObj.shopsellcoin = [];
			for(var i:int = 0;i < this.shopsellcoin.length;i++)
			{
				serializeObj.shopsellcoin.push(this.shopsellcoin[i].serialize());
			}
			serializeObj.friendworker = [];
			for(var i:int = 0;i < this.friendworker.length;i++)
			{
				serializeObj.friendworker.push(this.friendworker[i].serialize());
			}
			serializeObj.pet = [];
			for(var i:int = 0;i < this.pet.length;i++)
			{
				serializeObj.pet.push(this.pet[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):UserData
		{
			base = undefined;
			charges = new Vector.<ChargeItem>();
			builds = new Vector.<BuildingsCPP>();
			equipstar = new Vector.<EquipmentStarCPP>();
			cropland = new Vector.<CropLandCPP>();
			equipments = new Vector.<ProduceEquipCPP>();
			fruits = new Vector.<FruitCPP>();
			item = new Vector.<PropsItemCPP>();
			animals = new Vector.<AnimalCPP>();
			orders = new Vector.<OrderCPP>();
			truck = undefined;
			shipping = undefined;
			shipboxes = new Vector.<ShippingBoxCPP>();
			shop = new Vector.<ShopCPP>();
			task = new Vector.<TaskCPP>();
			mission = new Vector.<MissionCPP>();
			activity = new Vector.<ActivityCPP>();
			maildog = new Vector.<MaidDogCPP>();
			friendlytree = new Vector.<FriendlyTreeBasicCPP>();
			shopsellcoin = new Vector.<ShopSellCoinCPP>();
			friendworker = new Vector.<FriendWorkerCPP>();
			pet = new Vector.<UnlockPetCPP>();
			if(msgObj.hasOwnProperty("base"))
			{
				this.base = new Base(package_root).unserialize(msgObj.base);
			}
			for(var i:int = 0;i < msgObj.charges.length;i++)
			{
				this.charges.push(new ChargeItem(package_root).unserialize(msgObj.charges[i]));
			}
			for(var i:int = 0;i < msgObj.builds.length;i++)
			{
				this.builds.push(new BuildingsCPP(package_root).unserialize(msgObj.builds[i]));
			}
			for(var i:int = 0;i < msgObj.equipstar.length;i++)
			{
				this.equipstar.push(new EquipmentStarCPP(package_root).unserialize(msgObj.equipstar[i]));
			}
			for(var i:int = 0;i < msgObj.cropland.length;i++)
			{
				this.cropland.push(new CropLandCPP(package_root).unserialize(msgObj.cropland[i]));
			}
			for(var i:int = 0;i < msgObj.equipments.length;i++)
			{
				this.equipments.push(new ProduceEquipCPP(package_root).unserialize(msgObj.equipments[i]));
			}
			for(var i:int = 0;i < msgObj.fruits.length;i++)
			{
				this.fruits.push(new FruitCPP(package_root).unserialize(msgObj.fruits[i]));
			}
			for(var i:int = 0;i < msgObj.item.length;i++)
			{
				this.item.push(new PropsItemCPP(package_root).unserialize(msgObj.item[i]));
			}
			for(var i:int = 0;i < msgObj.animals.length;i++)
			{
				this.animals.push(new AnimalCPP(package_root).unserialize(msgObj.animals[i]));
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
			for(var i:int = 0;i < msgObj.shop.length;i++)
			{
				this.shop.push(new ShopCPP(package_root).unserialize(msgObj.shop[i]));
			}
			for(var i:int = 0;i < msgObj.task.length;i++)
			{
				this.task.push(new TaskCPP(package_root).unserialize(msgObj.task[i]));
			}
			for(var i:int = 0;i < msgObj.mission.length;i++)
			{
				this.mission.push(new MissionCPP(package_root).unserialize(msgObj.mission[i]));
			}
			for(var i:int = 0;i < msgObj.activity.length;i++)
			{
				this.activity.push(new ActivityCPP(package_root).unserialize(msgObj.activity[i]));
			}
			for(var i:int = 0;i < msgObj.maildog.length;i++)
			{
				this.maildog.push(new MaidDogCPP(package_root).unserialize(msgObj.maildog[i]));
			}
			for(var i:int = 0;i < msgObj.friendlytree.length;i++)
			{
				this.friendlytree.push(new FriendlyTreeBasicCPP(package_root).unserialize(msgObj.friendlytree[i]));
			}
			for(var i:int = 0;i < msgObj.shopsellcoin.length;i++)
			{
				this.shopsellcoin.push(new ShopSellCoinCPP(package_root).unserialize(msgObj.shopsellcoin[i]));
			}
			for(var i:int = 0;i < msgObj.friendworker.length;i++)
			{
				this.friendworker.push(new FriendWorkerCPP(package_root).unserialize(msgObj.friendworker[i]));
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
		public function decode(buffer:*):UserData
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}