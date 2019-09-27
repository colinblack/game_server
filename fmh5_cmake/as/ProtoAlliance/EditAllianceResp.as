package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class EditAllianceResp
	{
		public static const PROTO:String = "ProtoAlliance.EditAllianceResp";
		public var package_root:*;
		public  var message:*;
		public var alliance:AllianceCPP;
		public function EditAllianceResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			alliance = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.alliance = this.alliance.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):EditAllianceResp
		{
			alliance = undefined;
			this.alliance = new AllianceCPP(package_root).unserialize(msgObj.alliance);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):EditAllianceResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}