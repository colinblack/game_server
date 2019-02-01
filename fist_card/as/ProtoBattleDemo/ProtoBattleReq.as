package com.sanguo.game.server.connectlogic.common.message.ProtoBattleDemo
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoBattleReq
	{
		public static const PROTO:String = "ProtoBattleDemo.ProtoBattleReq";
		public var package_root:*;
		public  var message:*;
		public var battleid:int;
		public var ud:int;
		public var id:int;
		public var heroid:int;
		public var aimuid:int;
		public function ProtoBattleReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			battleid = undefined;
			ud = undefined;
			id = undefined;
			heroid = undefined;
			aimuid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.battleid = this.battleid;
			serializeObj.ud = this.ud;
			serializeObj.id = this.id;
			serializeObj.heroid = this.heroid;
			serializeObj.aimuid = this.aimuid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoBattleReq
		{
			battleid = undefined;
			ud = undefined;
			id = undefined;
			heroid = undefined;
			aimuid = undefined;
			this.battleid = msgObj.battleid;
			this.ud = msgObj.ud;
			this.id = msgObj.id;
			this.heroid = msgObj.heroid;
			this.aimuid = msgObj.aimuid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoBattleReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}