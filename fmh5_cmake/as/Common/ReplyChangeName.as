package com.sanguo.game.server.connectlogic.common.message.Common
{
	import laya.utils.Byte;
	public class ReplyChangeName
	{
		public static const PROTO:String = "Common.ReplyChangeName";
		public var package_root:*;
		public  var message:*;
		public var name:Byte;
		public var fig:Byte;
		public function ReplyChangeName(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			name = undefined;
			fig = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			this.name.pos = 0;
			this.fig.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyChangeName
		{
			name = undefined;
			fig = undefined;
			this.name = new Byte();
			this.name.writeArrayBuffer(msgObj.name);
			this.name.pos = 0;
			this.fig = new Byte();
			this.fig.writeArrayBuffer(msgObj.fig);
			this.fig.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyChangeName
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}