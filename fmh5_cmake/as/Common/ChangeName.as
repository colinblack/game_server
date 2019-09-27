package com.sanguo.game.server.connectlogic.common.message.Common
{
	import laya.utils.Byte;
	public class ChangeName
	{
		public static const PROTO:String = "Common.ChangeName";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var name:Byte;
		public var fig:Byte;
		public function ChangeName(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			name = undefined;
			fig = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			this.name.pos = 0;
			this.fig.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ChangeName
		{
			uid = undefined;
			name = undefined;
			fig = undefined;
			this.uid = msgObj.uid;
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
		public function decode(buffer:*):ChangeName
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}