package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class InivteUserInfoCPP
	{
		public static const PROTO:String = "User.InivteUserInfoCPP";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var name:Byte;
		public var fig:Byte;
		public function InivteUserInfoCPP(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
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
		public function unserialize(msgObj:*):InivteUserInfoCPP
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
		public function decode(buffer:*):InivteUserInfoCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}