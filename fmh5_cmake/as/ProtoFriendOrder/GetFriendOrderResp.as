package com.sanguo.game.server.connectlogic.common.message.ProtoFriendOrder
{
	import laya.utils.Byte;
	public class GetFriendOrderResp
	{
		public static const PROTO:String = "ProtoFriendOrder.GetFriendOrderResp";
		public var package_root:*;
		public  var message:*;
		public var arrayFoInfo:Vector.<FriendOrderInfo>;
		public function GetFriendOrderResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			arrayFoInfo = new Vector.<FriendOrderInfo>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.arrayFoInfo = [];
			for(var i:int = 0;i < this.arrayFoInfo.length;i++)
			{
				serializeObj.arrayFoInfo.push(this.arrayFoInfo[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetFriendOrderResp
		{
			arrayFoInfo = new Vector.<FriendOrderInfo>();
			for(var i:int = 0;i < msgObj.arrayFoInfo.length;i++)
			{
				this.arrayFoInfo.push(new FriendOrderInfo(package_root).unserialize(msgObj.arrayFoInfo[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetFriendOrderResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}