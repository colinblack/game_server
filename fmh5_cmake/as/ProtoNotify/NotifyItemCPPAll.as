package com.sanguo.game.server.connectlogic.common.message.ProtoNotify
{
	import laya.utils.Byte;
	public class NotifyItemCPPAll
	{
		public static const PROTO:String = "ProtoNotify.NotifyItemCPPAll";
		public var package_root:*;
		public  var message:*;
		public var notify:Vector.<NotifyItemCPP>;
		public function NotifyItemCPPAll(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			notify = new Vector.<NotifyItemCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.notify = [];
			for(var i:int = 0;i < this.notify.length;i++)
			{
				serializeObj.notify.push(this.notify[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):NotifyItemCPPAll
		{
			notify = new Vector.<NotifyItemCPP>();
			for(var i:int = 0;i < msgObj.notify.length;i++)
			{
				this.notify.push(new NotifyItemCPP(package_root).unserialize(msgObj.notify[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):NotifyItemCPPAll
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}