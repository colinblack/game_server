package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class ReplySysMail
	{
		public static const PROTO:String = "User.ReplySysMail";
		public var package_root:*;
		public  var message:*;
		public var mail:Vector.<SysMail>;
		public function ReplySysMail(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			mail = new Vector.<SysMail>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.mail = [];
			for(var i:int = 0;i < this.mail.length;i++)
			{
				serializeObj.mail.push(this.mail[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplySysMail
		{
			mail = new Vector.<SysMail>();
			for(var i:int = 0;i < msgObj.mail.length;i++)
			{
				this.mail.push(new SysMail(package_root).unserialize(msgObj.mail[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplySysMail
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}