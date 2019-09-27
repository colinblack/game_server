package com.sanguo.game.server.connectlogic.common.message.ProtoMailDog
{
	import laya.utils.Byte;
	public class GetMailDogInfoResp
	{
		public static const PROTO:String = "ProtoMailDog.GetMailDogInfoResp";
		public var package_root:*;
		public  var message:*;
		public var dog:Vector.<MaidDogCPP>;
		public var prosperity:ProsperityValueCPP;
		public var commons:CommonItemsCPP;
		public function GetMailDogInfoResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			dog = new Vector.<MaidDogCPP>();
			prosperity = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.dog = [];
			for(var i:int = 0;i < this.dog.length;i++)
			{
				serializeObj.dog.push(this.dog[i].serialize());
			}
			serializeObj.prosperity = this.prosperity.serialize();
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetMailDogInfoResp
		{
			dog = new Vector.<MaidDogCPP>();
			prosperity = undefined;
			commons = undefined;
			for(var i:int = 0;i < msgObj.dog.length;i++)
			{
				this.dog.push(new MaidDogCPP(package_root).unserialize(msgObj.dog[i]));
			}
			this.prosperity = new ProsperityValueCPP(package_root).unserialize(msgObj.prosperity);
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetMailDogInfoResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}