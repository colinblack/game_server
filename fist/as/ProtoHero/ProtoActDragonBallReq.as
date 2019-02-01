package com.sanguo.game.server.connectlogic.common.message.ProtoHero
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoActDragonBallReq
	{
		public static const PROTO:String = "ProtoHero.ProtoActDragonBallReq";
		public var package_root:*;
		public  var message:*;
		public var heroid:int;
		public var idx:int;
		public function ProtoActDragonBallReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			heroid = undefined;
			idx = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.heroid = this.heroid;
			serializeObj.idx = this.idx;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoActDragonBallReq
		{
			heroid = undefined;
			idx = undefined;
			this.heroid = msgObj.heroid;
			this.idx = msgObj.idx;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoActDragonBallReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}