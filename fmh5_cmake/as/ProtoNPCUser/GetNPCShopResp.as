package com.sanguo.game.server.connectlogic.common.message.ProtoNPCUser
{
	import laya.utils.Byte;
	public class GetNPCShopResp
	{
		public static const PROTO:String = "ProtoNPCUser.GetNPCShopResp";
		public var package_root:*;
		public  var message:*;
		public var shop:Vector.<NPCShopCPP>;
		public function GetNPCShopResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			shop = new Vector.<NPCShopCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.shop = [];
			for(var i:int = 0;i < this.shop.length;i++)
			{
				serializeObj.shop.push(this.shop[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetNPCShopResp
		{
			shop = new Vector.<NPCShopCPP>();
			for(var i:int = 0;i < msgObj.shop.length;i++)
			{
				this.shop.push(new NPCShopCPP(package_root).unserialize(msgObj.shop[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetNPCShopResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}