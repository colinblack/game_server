package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class OtherUser
	{
		public static const PROTO:String = "User.OtherUser";
		public var package_root:*;
		public  var message:*;
		public var base:Base;
		public var builds:Vector.<BuildingCPP>;
		public var cropland:Vector.<CropLandCPP>;
		public var equipments:Vector.<OthProduceCPP>;
		public var animals:Vector.<AnimalCPP>;
		public var equipmentstars:Vector.<EquipmentStarCPP>;
		public var fruits:Vector.<FruitCPP>;
		public var shopStatus:int;
		public var shipping:ShippingCPP;
		public var shipboxes:Vector.<ShippingBoxCPP>;
		public var friendlytree:FriendlyTreeCPP;
		public var theme:ThemeInfoResp;
		public var arraypet:Vector.<UnlockPetCPP>;
		public function OtherUser(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			base = undefined;
			builds = new Vector.<BuildingCPP>();
			cropland = new Vector.<CropLandCPP>();
			equipments = new Vector.<OthProduceCPP>();
			animals = new Vector.<AnimalCPP>();
			equipmentstars = new Vector.<EquipmentStarCPP>();
			fruits = new Vector.<FruitCPP>();
			shopStatus = undefined;
			shipping = undefined;
			shipboxes = new Vector.<ShippingBoxCPP>();
			friendlytree = undefined;
			theme = undefined;
			arraypet = new Vector.<UnlockPetCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.base = this.base.serialize();
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
			serializeObj.shopStatus = this.shopStatus;
			if(this.shipping!= undefined)
			{
				serializeObj.shipping = this.shipping.serialize();
			}
			serializeObj.shipboxes = [];
			for(var i:int = 0;i < this.shipboxes.length;i++)
			{
				serializeObj.shipboxes.push(this.shipboxes[i].serialize());
			}
			serializeObj.friendlytree = this.friendlytree.serialize();
			if(this.theme!= undefined)
			{
				serializeObj.theme = this.theme.serialize();
			}
			serializeObj.arraypet = [];
			for(var i:int = 0;i < this.arraypet.length;i++)
			{
				serializeObj.arraypet.push(this.arraypet[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):OtherUser
		{
			base = undefined;
			builds = new Vector.<BuildingCPP>();
			cropland = new Vector.<CropLandCPP>();
			equipments = new Vector.<OthProduceCPP>();
			animals = new Vector.<AnimalCPP>();
			equipmentstars = new Vector.<EquipmentStarCPP>();
			fruits = new Vector.<FruitCPP>();
			shopStatus = undefined;
			shipping = undefined;
			shipboxes = new Vector.<ShippingBoxCPP>();
			friendlytree = undefined;
			theme = undefined;
			arraypet = new Vector.<UnlockPetCPP>();
			this.base = new Base(package_root).unserialize(msgObj.base);
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
				this.equipments.push(new OthProduceCPP(package_root).unserialize(msgObj.equipments[i]));
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
			this.shopStatus = msgObj.shopStatus;
			if(msgObj.hasOwnProperty("shipping"))
			{
				this.shipping = new ShippingCPP(package_root).unserialize(msgObj.shipping);
			}
			for(var i:int = 0;i < msgObj.shipboxes.length;i++)
			{
				this.shipboxes.push(new ShippingBoxCPP(package_root).unserialize(msgObj.shipboxes[i]));
			}
			this.friendlytree = new FriendlyTreeCPP(package_root).unserialize(msgObj.friendlytree);
			if(msgObj.hasOwnProperty("theme"))
			{
				this.theme = new ThemeInfoResp(package_root).unserialize(msgObj.theme);
			}
			for(var i:int = 0;i < msgObj.arraypet.length;i++)
			{
				this.arraypet.push(new UnlockPetCPP(package_root).unserialize(msgObj.arraypet[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):OtherUser
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}