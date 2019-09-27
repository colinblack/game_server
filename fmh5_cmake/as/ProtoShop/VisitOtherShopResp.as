package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class VisitOtherShopResp
	{
		public static const PROTO:String = "ProtoShop.VisitOtherShopResp";
		public var package_root:*;
		public  var message:*;
		public var othuid:int;
		public var othshop:Vector.<ShopCPP>;
		public function VisitOtherShopResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			othuid = undefined;
			othshop = new Vector.<ShopCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.othuid = this.othuid;
			serializeObj.othshop = [];
			for(var i:int = 0;i < this.othshop.length;i++)
			{
				serializeObj.othshop.push(this.othshop[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):VisitOtherShopResp
		{
			othuid = undefined;
			othshop = new Vector.<ShopCPP>();
			this.othuid = msgObj.othuid;
			for(var i:int = 0;i < msgObj.othshop.length;i++)
			{
				this.othshop.push(new ShopCPP(package_root).unserialize(msgObj.othshop[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):VisitOtherShopResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}