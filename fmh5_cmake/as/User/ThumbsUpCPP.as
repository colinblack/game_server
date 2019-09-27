package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class ThumbsUpCPP
	{
		public static const PROTO:String = "User.ThumbsUpCPP";
		public var package_root:*;
		public  var message:*;
		public var index:Vector.<int>;
		public function ThumbsUpCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			index = new Vector.<int>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.index = [];
			for(var i:int = 0;i < this.index.length;i++)
			{
				serializeObj.index.push(this.index[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ThumbsUpCPP
		{
			index = new Vector.<int>();
			for(var i:int = 0;i < msgObj.index.length;i++)
			{
				this.index.push(msgObj.index[i]);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ThumbsUpCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}