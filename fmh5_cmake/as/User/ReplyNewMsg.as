package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class ReplyNewMsg
	{
		public static const PROTO:String = "User.ReplyNewMsg";
		public var package_root:*;
		public  var message:*;
		public var type:Vector.<int>;
		public function ReplyNewMsg(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			type = new Vector.<int>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.type = [];
			for(var i:int = 0;i < this.type.length;i++)
			{
				serializeObj.type.push(this.type[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyNewMsg
		{
			type = new Vector.<int>();
			for(var i:int = 0;i < msgObj.type.length;i++)
			{
				this.type.push(msgObj.type[i]);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyNewMsg
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}