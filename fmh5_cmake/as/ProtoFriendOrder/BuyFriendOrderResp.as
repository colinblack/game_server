package com.sanguo.game.server.connectlogic.common.message.ProtoFriendOrder
{
	import laya.utils.Byte;
	public class BuyFriendOrderResp
	{
		public static const PROTO:String = "ProtoFriendOrder.BuyFriendOrderResp";
		public var package_root:*;
		public  var message:*;
		public var index:int;
		public var newstatus:int;
		public var commons:CommonItemsCPP;
		public function BuyFriendOrderResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			index = undefined;
			newstatus = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.index = this.index;
			serializeObj.newstatus = this.newstatus;
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):BuyFriendOrderResp
		{
			index = undefined;
			newstatus = undefined;
			commons = undefined;
			this.index = msgObj.index;
			this.newstatus = msgObj.newstatus;
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
		public function decode(buffer:*):BuyFriendOrderResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}