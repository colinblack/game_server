package com.sanguo.game.server.connectlogic.common.message.ProtoFriendOrder
{
	import laya.utils.Byte;
	public class SendFriendOrderResp
	{
		public static const PROTO:String = "ProtoFriendOrder.SendFriendOrderResp";
		public var package_root:*;
		public  var message:*;
		public var basket:int;
		public var newSourceFo:FriendOrderInfo;
		public var commons:CommonItemsCPP;
		public function SendFriendOrderResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			basket = undefined;
			newSourceFo = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.basket = this.basket;
			serializeObj.newSourceFo = this.newSourceFo.serialize();
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):SendFriendOrderResp
		{
			basket = undefined;
			newSourceFo = undefined;
			commons = undefined;
			this.basket = msgObj.basket;
			this.newSourceFo = new FriendOrderInfo(package_root).unserialize(msgObj.newSourceFo);
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
		public function decode(buffer:*):SendFriendOrderResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}