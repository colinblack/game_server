package com.sanguo.game.server.connectlogic.common.message.ProtoChampionship
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class MatchUserInfoCPP
	{
		public static const PROTO:String = "ProtoChampionship.MatchUserInfoCPP";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var battleid:int;
		public var fig:String;
		public var name:String;
		public var grade:int;
		public var heroid:int;
		public var status:int;
		public function MatchUserInfoCPP(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			uid = undefined;
			battleid = undefined;
			fig = undefined;
			name = undefined;
			grade = undefined;
			heroid = undefined;
			status = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.battleid = this.battleid;
			if(this.fig!= undefined)
			{
				serializeObj.fig = this.fig;
			}
			if(this.name!= undefined)
			{
				serializeObj.name = this.name;
			}
			if(this.grade!= undefined)
			{
				serializeObj.grade = this.grade;
			}
			if(this.heroid!= undefined)
			{
				serializeObj.heroid = this.heroid;
			}
			if(this.status!= undefined)
			{
				serializeObj.status = this.status;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):MatchUserInfoCPP
		{
			uid = undefined;
			battleid = undefined;
			fig = undefined;
			name = undefined;
			grade = undefined;
			heroid = undefined;
			status = undefined;
			this.uid = msgObj.uid;
			this.battleid = msgObj.battleid;
			if(msgObj.hasOwnProperty("fig"))
			{
				this.fig = msgObj.fig;
			}
			if(msgObj.hasOwnProperty("name"))
			{
				this.name = msgObj.name;
			}
			if(msgObj.hasOwnProperty("grade"))
			{
				this.grade = msgObj.grade;
			}
			if(msgObj.hasOwnProperty("heroid"))
			{
				this.heroid = msgObj.heroid;
			}
			if(msgObj.hasOwnProperty("status"))
			{
				this.status = msgObj.status;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):MatchUserInfoCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}